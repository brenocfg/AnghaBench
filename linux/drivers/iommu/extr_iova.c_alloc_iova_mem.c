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
struct iova {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  iova_cache ; 
 struct iova* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iova *alloc_iova_mem(void)
{
	return kmem_cache_alloc(iova_cache, GFP_ATOMIC);
}