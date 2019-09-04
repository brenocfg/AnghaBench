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
struct TYPE_15__ {int /*<<< orphan*/  object; int /*<<< orphan*/  class; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  length; void* pointer; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; void* pointer; } ;
union acpi_operand_object {TYPE_7__ reference; TYPE_5__ integer; TYPE_4__ buffer; TYPE_1__ string; } ;
struct TYPE_16__ {int /*<<< orphan*/  handle; } ;
struct TYPE_14__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  pointer; } ;
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/  pointer; } ;
union acpi_object {int type; TYPE_8__ reference; TYPE_6__ integer; TYPE_3__ buffer; TYPE_2__ string; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 void* ACPI_ALLOCATE_ZEROED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_REFOF ; 
#define  ACPI_TYPE_ANY 132 
#define  ACPI_TYPE_BUFFER 131 
#define  ACPI_TYPE_INTEGER 130 
#define  ACPI_TYPE_LOCAL_REFERENCE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_copy_esimple_to_isimple ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_esimple_to_isimple(union acpi_object *external_object,
				union acpi_operand_object **ret_internal_object)
{
	union acpi_operand_object *internal_object;

	ACPI_FUNCTION_TRACE(ut_copy_esimple_to_isimple);

	/*
	 * Simple types supported are: String, Buffer, Integer
	 */
	switch (external_object->type) {
	case ACPI_TYPE_STRING:
	case ACPI_TYPE_BUFFER:
	case ACPI_TYPE_INTEGER:
	case ACPI_TYPE_LOCAL_REFERENCE:

		internal_object = acpi_ut_create_internal_object((u8)
								 external_object->
								 type);
		if (!internal_object) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
		break;

	case ACPI_TYPE_ANY:	/* This is the case for a NULL object */

		*ret_internal_object = NULL;
		return_ACPI_STATUS(AE_OK);

	default:

		/* All other types are not supported */

		ACPI_ERROR((AE_INFO,
			    "Unsupported object type, cannot convert to internal object: %s",
			    acpi_ut_get_type_name(external_object->type)));

		return_ACPI_STATUS(AE_SUPPORT);
	}

	/* Must COPY string and buffer contents */

	switch (external_object->type) {
	case ACPI_TYPE_STRING:

		internal_object->string.pointer =
		    ACPI_ALLOCATE_ZEROED((acpi_size)
					 external_object->string.length + 1);

		if (!internal_object->string.pointer) {
			goto error_exit;
		}

		memcpy(internal_object->string.pointer,
		       external_object->string.pointer,
		       external_object->string.length);

		internal_object->string.length = external_object->string.length;
		break;

	case ACPI_TYPE_BUFFER:

		internal_object->buffer.pointer =
		    ACPI_ALLOCATE_ZEROED(external_object->buffer.length);
		if (!internal_object->buffer.pointer) {
			goto error_exit;
		}

		memcpy(internal_object->buffer.pointer,
		       external_object->buffer.pointer,
		       external_object->buffer.length);

		internal_object->buffer.length = external_object->buffer.length;

		/* Mark buffer data valid */

		internal_object->buffer.flags |= AOPOBJ_DATA_VALID;
		break;

	case ACPI_TYPE_INTEGER:

		internal_object->integer.value = external_object->integer.value;
		break;

	case ACPI_TYPE_LOCAL_REFERENCE:

		/* An incoming reference is defined to be a namespace node */

		internal_object->reference.class = ACPI_REFCLASS_REFOF;
		internal_object->reference.object =
		    external_object->reference.handle;
		break;

	default:

		/* Other types can't get here */

		break;
	}

	*ret_internal_object = internal_object;
	return_ACPI_STATUS(AE_OK);

error_exit:
	acpi_ut_remove_reference(internal_object);
	return_ACPI_STATUS(AE_NO_MEMORY);
}