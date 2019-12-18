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
struct ipuv3_channel {int /*<<< orphan*/  num; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int ipu_fsu_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipu_idmac_link(struct ipuv3_channel *src, struct ipuv3_channel *sink)
{
	return ipu_fsu_link(src->ipu, src->num, sink->num);
}