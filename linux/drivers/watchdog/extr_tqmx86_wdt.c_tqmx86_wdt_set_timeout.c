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
typedef  int u8 ;
struct watchdog_device {unsigned int timeout; } ;
struct tqmx86_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ TQMX86_WDCFG ; 
 int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 struct tqmx86_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int tqmx86_wdt_set_timeout(struct watchdog_device *wdd, unsigned int t)
{
	struct tqmx86_wdt *priv = watchdog_get_drvdata(wdd);
	u8 val;

	t = roundup_pow_of_two(t);
	val = ilog2(t) | 0x90;
	val += 3; /* values 0,1,2 correspond to 0.125,0.25,0.5s timeouts */
	iowrite8(val, priv->io_base + TQMX86_WDCFG);

	wdd->timeout = t;

	return 0;
}