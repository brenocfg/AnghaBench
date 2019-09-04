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
typedef  int /*<<< orphan*/  u32 ;
struct m88rs6000t_dev {int /*<<< orphan*/  frequency_khz; TYPE_1__* client; } ;
struct dvb_frontend {struct m88rs6000t_dev* tuner_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int m88rs6000t_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct m88rs6000t_dev *dev = fe->tuner_priv;

	dev_dbg(&dev->client->dev, "\n");

	*frequency = dev->frequency_khz;
	return 0;
}