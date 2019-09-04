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
struct nvif_notify {int dummy; } ;

/* Variables and functions */
 int NVIF_NOTIFY_KEEP ; 

__attribute__((used)) static int
nv50_wndw_notify(struct nvif_notify *notify)
{
	return NVIF_NOTIFY_KEEP;
}