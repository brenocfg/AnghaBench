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
struct device {int dummy; } ;
struct auo_pixcir_ts_platdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct auo_pixcir_ts_platdata* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct auo_pixcir_ts_platdata *auo_pixcir_parse_dt(struct device *dev)
{
	return ERR_PTR(-EINVAL);
}