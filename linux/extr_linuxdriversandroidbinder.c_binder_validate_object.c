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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct flat_binder_object {int dummy; } ;
struct binder_object_header {int type; } ;
struct binder_fd_object {int dummy; } ;
struct binder_fd_array_object {int dummy; } ;
struct binder_buffer_object {int dummy; } ;
struct binder_buffer {int data_size; int data; } ;

/* Variables and functions */
#define  BINDER_TYPE_BINDER 134 
#define  BINDER_TYPE_FD 133 
#define  BINDER_TYPE_FDA 132 
#define  BINDER_TYPE_HANDLE 131 
#define  BINDER_TYPE_PTR 130 
#define  BINDER_TYPE_WEAK_BINDER 129 
#define  BINDER_TYPE_WEAK_HANDLE 128 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 

__attribute__((used)) static size_t binder_validate_object(struct binder_buffer *buffer, u64 offset)
{
	/* Check if we can read a header first */
	struct binder_object_header *hdr;
	size_t object_size = 0;

	if (buffer->data_size < sizeof(*hdr) ||
	    offset > buffer->data_size - sizeof(*hdr) ||
	    !IS_ALIGNED(offset, sizeof(u32)))
		return 0;

	/* Ok, now see if we can read a complete object. */
	hdr = (struct binder_object_header *)(buffer->data + offset);
	switch (hdr->type) {
	case BINDER_TYPE_BINDER:
	case BINDER_TYPE_WEAK_BINDER:
	case BINDER_TYPE_HANDLE:
	case BINDER_TYPE_WEAK_HANDLE:
		object_size = sizeof(struct flat_binder_object);
		break;
	case BINDER_TYPE_FD:
		object_size = sizeof(struct binder_fd_object);
		break;
	case BINDER_TYPE_PTR:
		object_size = sizeof(struct binder_buffer_object);
		break;
	case BINDER_TYPE_FDA:
		object_size = sizeof(struct binder_fd_array_object);
		break;
	default:
		return 0;
	}
	if (offset <= buffer->data_size - object_size &&
	    buffer->data_size >= object_size)
		return object_size;
	else
		return 0;
}