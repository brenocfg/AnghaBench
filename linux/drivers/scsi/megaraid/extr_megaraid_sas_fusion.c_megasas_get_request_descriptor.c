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
typedef  union MEGASAS_REQUEST_DESCRIPTOR_UNION {int dummy; } MEGASAS_REQUEST_DESCRIPTOR_UNION ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct fusion_context {int /*<<< orphan*/ * req_frames_desc; } ;

/* Variables and functions */

__attribute__((used)) static union MEGASAS_REQUEST_DESCRIPTOR_UNION *
megasas_get_request_descriptor(struct megasas_instance *instance, u16 index)
{
	u8 *p;
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;
	p = fusion->req_frames_desc +
		sizeof(union MEGASAS_REQUEST_DESCRIPTOR_UNION) * index;

	return (union MEGASAS_REQUEST_DESCRIPTOR_UNION *)p;
}