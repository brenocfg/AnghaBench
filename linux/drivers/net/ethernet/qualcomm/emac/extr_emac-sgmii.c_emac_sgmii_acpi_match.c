#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sgmii_ops {int dummy; } ;
struct device {int dummy; } ;
struct acpi_device_id {char* id; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 struct acpi_device_id* acpi_match_device (struct acpi_device_id const*,struct device*) ; 
 struct sgmii_ops qdf2400_ops ; 
 struct sgmii_ops qdf2432_ops ; 

__attribute__((used)) static int emac_sgmii_acpi_match(struct device *dev, void *data)
{
#ifdef CONFIG_ACPI
	static const struct acpi_device_id match_table[] = {
		{
			.id = "QCOM8071",
		},
		{}
	};
	const struct acpi_device_id *id = acpi_match_device(match_table, dev);
	struct sgmii_ops **ops = data;

	if (id) {
		acpi_handle handle = ACPI_HANDLE(dev);
		unsigned long long hrv;
		acpi_status status;

		status = acpi_evaluate_integer(handle, "_HRV", NULL, &hrv);
		if (status) {
			if (status == AE_NOT_FOUND)
				/* Older versions of the QDF2432 ACPI tables do
				 * not have an _HRV property.
				 */
				hrv = 1;
			else
				/* Something is wrong with the tables */
				return 0;
		}

		switch (hrv) {
		case 1:
			*ops = &qdf2432_ops;
			return 1;
		case 2:
			*ops = &qdf2400_ops;
			return 1;
		}
	}
#endif

	return 0;
}