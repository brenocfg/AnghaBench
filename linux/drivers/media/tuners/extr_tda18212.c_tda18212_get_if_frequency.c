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
typedef  int /*<<< orphan*/  u32 ;
struct tda18212_dev {int /*<<< orphan*/  if_frequency; } ;
struct dvb_frontend {struct tda18212_dev* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int tda18212_get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct tda18212_dev *dev = fe->tuner_priv;

	*frequency = dev->if_frequency;

	return 0;
}