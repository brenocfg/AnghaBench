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
struct resource {scalar_t__ end; scalar_t__ start; } ;
struct gpmc_cs_data {struct resource mem; } ;

/* Variables and functions */
 struct gpmc_cs_data* gpmc_cs ; 
 int /*<<< orphan*/  gpmc_mem_lock ; 
 int release_resource (struct resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmc_cs_delete_mem(int cs)
{
	struct gpmc_cs_data *gpmc = &gpmc_cs[cs];
	struct resource *res = &gpmc->mem;
	int r;

	spin_lock(&gpmc_mem_lock);
	r = release_resource(res);
	res->start = 0;
	res->end = 0;
	spin_unlock(&gpmc_mem_lock);

	return r;
}