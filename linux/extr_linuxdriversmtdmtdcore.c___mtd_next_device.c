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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct mtd_info* idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mtd_idr ; 

struct mtd_info *__mtd_next_device(int i)
{
	return idr_get_next(&mtd_idr, &i);
}