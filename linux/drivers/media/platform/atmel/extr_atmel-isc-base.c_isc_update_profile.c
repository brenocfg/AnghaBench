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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct isc_device {int /*<<< orphan*/  v4l2_dev; struct regmap* regmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ISC_CTRLEN ; 
 int /*<<< orphan*/  ISC_CTRLSR ; 
 int ISC_CTRL_UPPRO ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int isc_update_profile(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	u32 sr;
	int counter = 100;

	regmap_write(regmap, ISC_CTRLEN, ISC_CTRL_UPPRO);

	regmap_read(regmap, ISC_CTRLSR, &sr);
	while ((sr & ISC_CTRL_UPPRO) && counter--) {
		usleep_range(1000, 2000);
		regmap_read(regmap, ISC_CTRLSR, &sr);
	}

	if (counter < 0) {
		v4l2_warn(&isc->v4l2_dev, "Time out to update profile\n");
		return -ETIMEDOUT;
	}

	return 0;
}