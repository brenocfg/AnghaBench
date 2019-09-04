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
typedef  int u8 ;
typedef  int u32 ;
struct aml_resource_end_tag {int dummy; } ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  (* acpi_walk_aml_callback ) (int*,int,int,int,void**) ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_ut_get_descriptor_length (int*) ; 
 scalar_t__ acpi_ut_get_resource_type (int*) ; 
 int /*<<< orphan*/  acpi_ut_validate_resource (struct acpi_walk_state*,int*,int*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_walk_aml_resources ; 

acpi_status
acpi_ut_walk_aml_resources(struct acpi_walk_state *walk_state,
			   u8 *aml,
			   acpi_size aml_length,
			   acpi_walk_aml_callback user_function, void **context)
{
	acpi_status status;
	u8 *end_aml;
	u8 resource_index;
	u32 length;
	u32 offset = 0;
	u8 end_tag[2] = { 0x79, 0x00 };

	ACPI_FUNCTION_TRACE(ut_walk_aml_resources);

	/* The absolute minimum resource template is one end_tag descriptor */

	if (aml_length < sizeof(struct aml_resource_end_tag)) {
		return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
	}

	/* Point to the end of the resource template buffer */

	end_aml = aml + aml_length;

	/* Walk the byte list, abort on any invalid descriptor type or length */

	while (aml < end_aml) {

		/* Validate the Resource Type and Resource Length */

		status =
		    acpi_ut_validate_resource(walk_state, aml, &resource_index);
		if (ACPI_FAILURE(status)) {
			/*
			 * Exit on failure. Cannot continue because the descriptor
			 * length may be bogus also.
			 */
			return_ACPI_STATUS(status);
		}

		/* Get the length of this descriptor */

		length = acpi_ut_get_descriptor_length(aml);

		/* Invoke the user function */

		if (user_function) {
			status =
			    user_function(aml, length, offset, resource_index,
					  context);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}

		/* An end_tag descriptor terminates this resource template */

		if (acpi_ut_get_resource_type(aml) ==
		    ACPI_RESOURCE_NAME_END_TAG) {
			/*
			 * There must be at least one more byte in the buffer for
			 * the 2nd byte of the end_tag
			 */
			if ((aml + 1) >= end_aml) {
				return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
			}

			/*
			 * Don't attempt to perform any validation on the 2nd byte.
			 * Although all known ASL compilers insert a zero for the 2nd
			 * byte, it can also be a checksum (as per the ACPI spec),
			 * and this is occasionally seen in the field. July 2017.
			 */

			/* Return the pointer to the end_tag if requested */

			if (!user_function) {
				*context = aml;
			}

			/* Normal exit */

			return_ACPI_STATUS(AE_OK);
		}

		aml += length;
		offset += length;
	}

	/* Did not find an end_tag descriptor */

	if (user_function) {

		/* Insert an end_tag anyway. acpi_rs_get_list_length always leaves room */

		(void)acpi_ut_validate_resource(walk_state, end_tag,
						&resource_index);
		status =
		    user_function(end_tag, 2, offset, resource_index, context);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
}