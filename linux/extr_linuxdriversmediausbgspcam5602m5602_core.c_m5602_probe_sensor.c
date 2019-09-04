#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sd {TYPE_1__* sensor; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* probe ) (struct sd*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__ mt9m111 ; 
 TYPE_1__ ov7660 ; 
 TYPE_1__ ov9650 ; 
 TYPE_1__ po1030 ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_1__ s5k4aa ; 
 TYPE_1__ s5k83a ; 
 int /*<<< orphan*/  stub1 (struct sd*) ; 
 int /*<<< orphan*/  stub2 (struct sd*) ; 
 int /*<<< orphan*/  stub3 (struct sd*) ; 
 int /*<<< orphan*/  stub4 (struct sd*) ; 
 int /*<<< orphan*/  stub5 (struct sd*) ; 
 int /*<<< orphan*/  stub6 (struct sd*) ; 

__attribute__((used)) static int m5602_probe_sensor(struct sd *sd)
{
	/* Try the po1030 */
	sd->sensor = &po1030;
	if (!sd->sensor->probe(sd))
		return 0;

	/* Try the mt9m111 sensor */
	sd->sensor = &mt9m111;
	if (!sd->sensor->probe(sd))
		return 0;

	/* Try the s5k4aa */
	sd->sensor = &s5k4aa;
	if (!sd->sensor->probe(sd))
		return 0;

	/* Try the ov9650 */
	sd->sensor = &ov9650;
	if (!sd->sensor->probe(sd))
		return 0;

	/* Try the ov7660 */
	sd->sensor = &ov7660;
	if (!sd->sensor->probe(sd))
		return 0;

	/* Try the s5k83a */
	sd->sensor = &s5k83a;
	if (!sd->sensor->probe(sd))
		return 0;

	/* More sensor probe function goes here */
	pr_info("Failed to find a sensor\n");
	sd->sensor = NULL;
	return -ENODEV;
}