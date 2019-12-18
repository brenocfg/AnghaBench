#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct v4l2_fract {scalar_t__ denominator; scalar_t__ numerator; } ;
struct imx_media_fim {int enabled; int /*<<< orphan*/  nominal; TYPE_1__* sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST_ULL (unsigned long long,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void update_fim_nominal(struct imx_media_fim *fim,
			       const struct v4l2_fract *fi)
{
	if (fi->denominator == 0) {
		dev_dbg(fim->sd->dev, "no frame interval, FIM disabled\n");
		fim->enabled = false;
		return;
	}

	fim->nominal = DIV_ROUND_CLOSEST_ULL(1000000ULL * (u64)fi->numerator,
					     fi->denominator);

	dev_dbg(fim->sd->dev, "FI=%lu usec\n", fim->nominal);
}