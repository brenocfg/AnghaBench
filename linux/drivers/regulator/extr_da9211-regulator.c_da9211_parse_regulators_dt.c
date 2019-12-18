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
struct da9211_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct da9211_pdata* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct da9211_pdata *da9211_parse_regulators_dt(
		struct device *dev)
{
	return ERR_PTR(-ENODEV);
}