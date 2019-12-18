#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int value; } ;
struct TYPE_4__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
struct st_sensor_data {TYPE_3__* mount_matrix; int /*<<< orphan*/  dev; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  ext_info; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_6__ {char** rotation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ AE_NOT_FOUND ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 TYPE_3__* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  mount_matrix_ext_info ; 

__attribute__((used)) static int apply_acpi_orientation(struct iio_dev *indio_dev,
				  struct iio_chan_spec *channels)
{
#ifdef CONFIG_ACPI
	struct st_sensor_data *adata = iio_priv(indio_dev);
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	struct acpi_device *adev;
	union acpi_object *ont;
	union acpi_object *elements;
	acpi_status status;
	int ret = -EINVAL;
	unsigned int val;
	int i, j;
	int final_ont[3][3] = { { 0 }, };

	/* For some reason, ST's _ONT translation does not apply directly
	 * to the data read from the sensor. Another translation must be
	 * performed first, as described by the matrix below. Perhaps
	 * ST required this specific translation for the first product
	 * where the device was mounted?
	 */
	const int default_ont[3][3] = {
		{  0,  1,  0 },
		{ -1,  0,  0 },
		{  0,  0, -1 },
	};


	adev = ACPI_COMPANION(adata->dev);
	if (!adev)
		return 0;

	/* Read _ONT data, which should be a package of 6 integers. */
	status = acpi_evaluate_object(adev->handle, "_ONT", NULL, &buffer);
	if (status == AE_NOT_FOUND) {
		return 0;
	} else if (ACPI_FAILURE(status)) {
		dev_warn(&indio_dev->dev, "failed to execute _ONT: %d\n",
			 status);
		return status;
	}

	ont = buffer.pointer;
	if (ont->type != ACPI_TYPE_PACKAGE || ont->package.count != 6)
		goto out;

	/* The first 3 integers provide axis order information.
	 * e.g. 0 1 2 would indicate normal X,Y,Z ordering.
	 * e.g. 1 0 2 indicates that data arrives in order Y,X,Z.
	 */
	elements = ont->package.elements;
	for (i = 0; i < 3; i++) {
		if (elements[i].type != ACPI_TYPE_INTEGER)
			goto out;

		val = elements[i].integer.value;
		if (val > 2)
			goto out;

		/* Avoiding full matrix multiplication, we simply reorder the
		 * columns in the default_ont matrix according to the
		 * ordering provided by _ONT.
		 */
		final_ont[0][i] = default_ont[0][val];
		final_ont[1][i] = default_ont[1][val];
		final_ont[2][i] = default_ont[2][val];
	}

	/* The final 3 integers provide sign flip information.
	 * 0 means no change, 1 means flip.
	 * e.g. 0 0 1 means that Z data should be sign-flipped.
	 * This is applied after the axis reordering from above.
	 */
	elements += 3;
	for (i = 0; i < 3; i++) {
		if (elements[i].type != ACPI_TYPE_INTEGER)
			goto out;

		val = elements[i].integer.value;
		if (val != 0 && val != 1)
			goto out;
		if (!val)
			continue;

		/* Flip the values in the indicated column */
		final_ont[0][i] *= -1;
		final_ont[1][i] *= -1;
		final_ont[2][i] *= -1;
	}

	/* Convert our integer matrix to a string-based iio_mount_matrix */
	adata->mount_matrix = devm_kmalloc(&indio_dev->dev,
					   sizeof(*adata->mount_matrix),
					   GFP_KERNEL);
	if (!adata->mount_matrix) {
		ret = -ENOMEM;
		goto out;
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			int matrix_val = final_ont[i][j];
			char *str_value;

			switch (matrix_val) {
			case -1:
				str_value = "-1";
				break;
			case 0:
				str_value = "0";
				break;
			case 1:
				str_value = "1";
				break;
			default:
				goto out;
			}
			adata->mount_matrix->rotation[i * 3 + j] = str_value;
		}
	}

	/* Expose the mount matrix via ext_info */
	for (i = 0; i < indio_dev->num_channels; i++)
		channels[i].ext_info = mount_matrix_ext_info;

	ret = 0;
	dev_info(&indio_dev->dev, "computed mount matrix from ACPI\n");

out:
	kfree(buffer.pointer);
	return ret;
#else /* !CONFIG_ACPI */
	return 0;
#endif
}