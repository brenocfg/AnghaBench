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
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  saa7134_set_decoder (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_call_empress (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

void saa7134_set_tvnorm_hw(struct saa7134_dev *dev)
{
	saa7134_set_decoder(dev);

	saa_call_all(dev, video, s_std, dev->tvnorm->id);
	/* Set the correct norm for the saa6752hs. This function
	   does nothing if there is no saa6752hs. */
	saa_call_empress(dev, video, s_std, dev->tvnorm->id);
}