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
struct vmw_private {int dummy; } ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */
 struct ttm_mem_global ttm_mem_glob ; 

__attribute__((used)) static inline struct ttm_mem_global *vmw_mem_glob(struct vmw_private *dev_priv)
{
	return &ttm_mem_glob;
}