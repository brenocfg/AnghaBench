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
struct ib_mad_private {size_t mad_size; } ;
struct ib_grh {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t mad_priv_dma_size(const struct ib_mad_private *mp)
{
	return sizeof(struct ib_grh) + mp->mad_size;
}