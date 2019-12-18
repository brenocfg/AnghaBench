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
struct sxgbe_desc_ops {int dummy; } ;

/* Variables and functions */
 struct sxgbe_desc_ops const desc_ops ; 

const struct sxgbe_desc_ops *sxgbe_get_desc_ops(void)
{
	return &desc_ops;
}