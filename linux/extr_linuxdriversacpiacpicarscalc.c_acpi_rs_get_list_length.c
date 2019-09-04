#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t type; size_t resource_length; } ;
struct TYPE_15__ {scalar_t__ vendor_length; scalar_t__ res_source_offset; scalar_t__ vendor_offset; } ;
struct TYPE_14__ {scalar_t__ vendor_length; scalar_t__ res_source_offset; scalar_t__ vendor_offset; } ;
struct TYPE_13__ {scalar_t__ vendor_length; scalar_t__ pin_table_offset; scalar_t__ vendor_offset; } ;
struct TYPE_12__ {scalar_t__ pin_table_offset; scalar_t__ vendor_length; scalar_t__ vendor_offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  resource_length; } ;
struct TYPE_10__ {scalar_t__ pin_table_offset; scalar_t__ vendor_length; scalar_t__ vendor_offset; } ;
struct TYPE_9__ {scalar_t__ pin_table_offset; scalar_t__ vendor_length; scalar_t__ vendor_offset; } ;
union aml_resource {TYPE_8__ common_serial_bus; TYPE_7__ pin_group_config; TYPE_6__ pin_group_function; TYPE_5__ pin_group; TYPE_4__ pin_config; TYPE_3__ large_header; TYPE_2__ pin_function; TYPE_1__ gpio; } ;
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct aml_resource_large_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_RESOURCES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_16_TO_16 (int*,size_t*) ; 
#define  ACPI_RESOURCE_NAME_ADDRESS16 143 
#define  ACPI_RESOURCE_NAME_ADDRESS32 142 
#define  ACPI_RESOURCE_NAME_ADDRESS64 141 
#define  ACPI_RESOURCE_NAME_DMA 140 
#define  ACPI_RESOURCE_NAME_END_TAG 139 
#define  ACPI_RESOURCE_NAME_EXTENDED_IRQ 138 
#define  ACPI_RESOURCE_NAME_GPIO 137 
#define  ACPI_RESOURCE_NAME_IRQ 136 
#define  ACPI_RESOURCE_NAME_PIN_CONFIG 135 
#define  ACPI_RESOURCE_NAME_PIN_FUNCTION 134 
#define  ACPI_RESOURCE_NAME_PIN_GROUP 133 
#define  ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG 132 
#define  ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION 131 
#define  ACPI_RESOURCE_NAME_SERIAL_BUS 130 
#define  ACPI_RESOURCE_NAME_VENDOR_LARGE 129 
#define  ACPI_RESOURCE_NAME_VENDOR_SMALL 128 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
 int /*<<< orphan*/  ACPI_RS_SIZE_MIN ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t* acpi_gbl_resource_aml_serial_bus_sizes ; 
 size_t* acpi_gbl_resource_aml_sizes ; 
 int* acpi_gbl_resource_struct_serial_bus_sizes ; 
 int* acpi_gbl_resource_struct_sizes ; 
 int acpi_rs_count_set_bits (size_t) ; 
 int acpi_rs_stream_option_length (int,size_t) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_length (size_t*) ; 
 int acpi_ut_get_resource_header_length (size_t*) ; 
 int acpi_ut_get_resource_length (size_t*) ; 
 int const acpi_ut_get_resource_type (size_t*) ; 
 int /*<<< orphan*/  acpi_ut_validate_resource (int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_get_list_length ; 

acpi_status
acpi_rs_get_list_length(u8 *aml_buffer,
			u32 aml_buffer_length, acpi_size *size_needed)
{
	acpi_status status;
	u8 *end_aml;
	u8 *buffer;
	u32 buffer_size;
	u16 temp16;
	u16 resource_length;
	u32 extra_struct_bytes;
	u8 resource_index;
	u8 minimum_aml_resource_length;
	union aml_resource *aml_resource;

	ACPI_FUNCTION_TRACE(rs_get_list_length);

	*size_needed = ACPI_RS_SIZE_MIN;	/* Minimum size is one end_tag */
	end_aml = aml_buffer + aml_buffer_length;

	/* Walk the list of AML resource descriptors */

	while (aml_buffer < end_aml) {

		/* Validate the Resource Type and Resource Length */

		status =
		    acpi_ut_validate_resource(NULL, aml_buffer,
					      &resource_index);
		if (ACPI_FAILURE(status)) {
			/*
			 * Exit on failure. Cannot continue because the descriptor length
			 * may be bogus also.
			 */
			return_ACPI_STATUS(status);
		}

		aml_resource = (void *)aml_buffer;

		/* Get the resource length and base (minimum) AML size */

		resource_length = acpi_ut_get_resource_length(aml_buffer);
		minimum_aml_resource_length =
		    acpi_gbl_resource_aml_sizes[resource_index];

		/*
		 * Augment the size for descriptors with optional
		 * and/or variable length fields
		 */
		extra_struct_bytes = 0;
		buffer =
		    aml_buffer + acpi_ut_get_resource_header_length(aml_buffer);

		switch (acpi_ut_get_resource_type(aml_buffer)) {
		case ACPI_RESOURCE_NAME_IRQ:
			/*
			 * IRQ Resource:
			 * Get the number of bits set in the 16-bit IRQ mask
			 */
			ACPI_MOVE_16_TO_16(&temp16, buffer);
			extra_struct_bytes = acpi_rs_count_set_bits(temp16);
			break;

		case ACPI_RESOURCE_NAME_DMA:
			/*
			 * DMA Resource:
			 * Get the number of bits set in the 8-bit DMA mask
			 */
			extra_struct_bytes = acpi_rs_count_set_bits(*buffer);
			break;

		case ACPI_RESOURCE_NAME_VENDOR_SMALL:
		case ACPI_RESOURCE_NAME_VENDOR_LARGE:
			/*
			 * Vendor Resource:
			 * Get the number of vendor data bytes
			 */
			extra_struct_bytes = resource_length;

			/*
			 * There is already one byte included in the minimum
			 * descriptor size. If there are extra struct bytes,
			 * subtract one from the count.
			 */
			if (extra_struct_bytes) {
				extra_struct_bytes--;
			}
			break;

		case ACPI_RESOURCE_NAME_END_TAG:
			/*
			 * End Tag: This is the normal exit
			 */
			return_ACPI_STATUS(AE_OK);

		case ACPI_RESOURCE_NAME_ADDRESS32:
		case ACPI_RESOURCE_NAME_ADDRESS16:
		case ACPI_RESOURCE_NAME_ADDRESS64:
			/*
			 * Address Resource:
			 * Add the size of the optional resource_source
			 */
			extra_struct_bytes =
			    acpi_rs_stream_option_length(resource_length,
							 minimum_aml_resource_length);
			break;

		case ACPI_RESOURCE_NAME_EXTENDED_IRQ:
			/*
			 * Extended IRQ Resource:
			 * Using the interrupt_table_length, add 4 bytes for each additional
			 * interrupt. Note: at least one interrupt is required and is
			 * included in the minimum descriptor size (reason for the -1)
			 */
			extra_struct_bytes = (buffer[1] - 1) * sizeof(u32);

			/* Add the size of the optional resource_source */

			extra_struct_bytes +=
			    acpi_rs_stream_option_length(resource_length -
							 extra_struct_bytes,
							 minimum_aml_resource_length);
			break;

		case ACPI_RESOURCE_NAME_GPIO:

			/* Vendor data is optional */

			if (aml_resource->gpio.vendor_length) {
				extra_struct_bytes +=
				    aml_resource->gpio.vendor_offset -
				    aml_resource->gpio.pin_table_offset +
				    aml_resource->gpio.vendor_length;
			} else {
				extra_struct_bytes +=
				    aml_resource->large_header.resource_length +
				    sizeof(struct aml_resource_large_header) -
				    aml_resource->gpio.pin_table_offset;
			}
			break;

		case ACPI_RESOURCE_NAME_PIN_FUNCTION:

			/* Vendor data is optional */

			if (aml_resource->pin_function.vendor_length) {
				extra_struct_bytes +=
				    aml_resource->pin_function.vendor_offset -
				    aml_resource->pin_function.
				    pin_table_offset +
				    aml_resource->pin_function.vendor_length;
			} else {
				extra_struct_bytes +=
				    aml_resource->large_header.resource_length +
				    sizeof(struct aml_resource_large_header) -
				    aml_resource->pin_function.pin_table_offset;
			}
			break;

		case ACPI_RESOURCE_NAME_SERIAL_BUS:

			minimum_aml_resource_length =
			    acpi_gbl_resource_aml_serial_bus_sizes
			    [aml_resource->common_serial_bus.type];
			extra_struct_bytes +=
			    aml_resource->common_serial_bus.resource_length -
			    minimum_aml_resource_length;
			break;

		case ACPI_RESOURCE_NAME_PIN_CONFIG:

			/* Vendor data is optional */

			if (aml_resource->pin_config.vendor_length) {
				extra_struct_bytes +=
				    aml_resource->pin_config.vendor_offset -
				    aml_resource->pin_config.pin_table_offset +
				    aml_resource->pin_config.vendor_length;
			} else {
				extra_struct_bytes +=
				    aml_resource->large_header.resource_length +
				    sizeof(struct aml_resource_large_header) -
				    aml_resource->pin_config.pin_table_offset;
			}
			break;

		case ACPI_RESOURCE_NAME_PIN_GROUP:

			extra_struct_bytes +=
			    aml_resource->pin_group.vendor_offset -
			    aml_resource->pin_group.pin_table_offset +
			    aml_resource->pin_group.vendor_length;

			break;

		case ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION:

			extra_struct_bytes +=
			    aml_resource->pin_group_function.vendor_offset -
			    aml_resource->pin_group_function.res_source_offset +
			    aml_resource->pin_group_function.vendor_length;

			break;

		case ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG:

			extra_struct_bytes +=
			    aml_resource->pin_group_config.vendor_offset -
			    aml_resource->pin_group_config.res_source_offset +
			    aml_resource->pin_group_config.vendor_length;

			break;

		default:

			break;
		}

		/*
		 * Update the required buffer size for the internal descriptor structs
		 *
		 * Important: Round the size up for the appropriate alignment. This
		 * is a requirement on IA64.
		 */
		if (acpi_ut_get_resource_type(aml_buffer) ==
		    ACPI_RESOURCE_NAME_SERIAL_BUS) {
			buffer_size =
			    acpi_gbl_resource_struct_serial_bus_sizes
			    [aml_resource->common_serial_bus.type] +
			    extra_struct_bytes;
		} else {
			buffer_size =
			    acpi_gbl_resource_struct_sizes[resource_index] +
			    extra_struct_bytes;
		}

		buffer_size = (u32)ACPI_ROUND_UP_TO_NATIVE_WORD(buffer_size);
		*size_needed += buffer_size;

		ACPI_DEBUG_PRINT((ACPI_DB_RESOURCES,
				  "Type %.2X, AmlLength %.2X InternalLength %.2X\n",
				  acpi_ut_get_resource_type(aml_buffer),
				  acpi_ut_get_descriptor_length(aml_buffer),
				  buffer_size));

		/*
		 * Point to the next resource within the AML stream using the length
		 * contained in the resource descriptor header
		 */
		aml_buffer += acpi_ut_get_descriptor_length(aml_buffer);
	}

	/* Did not find an end_tag resource descriptor */

	return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
}