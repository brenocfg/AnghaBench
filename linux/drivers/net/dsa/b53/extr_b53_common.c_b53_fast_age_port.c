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
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_FAST_AGE_PORT_CTRL ; 
 int /*<<< orphan*/  FAST_AGE_PORT ; 
 int b53_flush_arl (struct b53_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b53_fast_age_port(struct b53_device *dev, int port)
{
	b53_write8(dev, B53_CTRL_PAGE, B53_FAST_AGE_PORT_CTRL, port);

	return b53_flush_arl(dev, FAST_AGE_PORT);
}