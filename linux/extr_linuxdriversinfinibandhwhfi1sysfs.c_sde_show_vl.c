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
struct sdma_engine {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int sdma_engine_get_vl (struct sdma_engine*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t sde_show_vl(struct sdma_engine *sde, char *buf)
{
	int vl;

	vl = sdma_engine_get_vl(sde);
	if (vl < 0)
		return vl;

	return snprintf(buf, PAGE_SIZE, "%d\n", vl);
}