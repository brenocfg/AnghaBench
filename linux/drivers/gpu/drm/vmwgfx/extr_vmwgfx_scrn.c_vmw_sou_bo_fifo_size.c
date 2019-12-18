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
typedef  int uint32_t ;
struct vmw_kms_sou_define_gmrfb {int dummy; } ;
struct vmw_kms_sou_bo_blit {int dummy; } ;
struct vmw_du_update_plane {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t vmw_sou_bo_fifo_size(struct vmw_du_update_plane *update,
				     uint32_t num_hits)
{
	return sizeof(struct vmw_kms_sou_define_gmrfb) +
		sizeof(struct vmw_kms_sou_bo_blit) * num_hits;
}