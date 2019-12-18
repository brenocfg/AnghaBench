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
struct TYPE_2__ {int rt; } ;
struct rt2x00_dev {TYPE_1__ chip; } ;

/* Variables and functions */
#define  RT3070 141 
#define  RT3071 140 
#define  RT3090 139 
#define  RT3290 138 
#define  RT3352 137 
#define  RT3390 136 
#define  RT3572 135 
#define  RT3593 134 
#define  RT3883 133 
#define  RT5350 132 
#define  RT5390 131 
#define  RT5392 130 
#define  RT5592 129 
#define  RT6352 128 
 int /*<<< orphan*/  rt2800_init_rfcsr_305x_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_30xx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3290 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3352 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3390 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3572 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3593 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_3883 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_5350 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_5390 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_5392 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_5592 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr_6352 (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_is_305x_soc (struct rt2x00_dev*) ; 

__attribute__((used)) static void rt2800_init_rfcsr(struct rt2x00_dev *rt2x00dev)
{
	if (rt2800_is_305x_soc(rt2x00dev)) {
		rt2800_init_rfcsr_305x_soc(rt2x00dev);
		return;
	}

	switch (rt2x00dev->chip.rt) {
	case RT3070:
	case RT3071:
	case RT3090:
		rt2800_init_rfcsr_30xx(rt2x00dev);
		break;
	case RT3290:
		rt2800_init_rfcsr_3290(rt2x00dev);
		break;
	case RT3352:
		rt2800_init_rfcsr_3352(rt2x00dev);
		break;
	case RT3390:
		rt2800_init_rfcsr_3390(rt2x00dev);
		break;
	case RT3883:
		rt2800_init_rfcsr_3883(rt2x00dev);
		break;
	case RT3572:
		rt2800_init_rfcsr_3572(rt2x00dev);
		break;
	case RT3593:
		rt2800_init_rfcsr_3593(rt2x00dev);
		break;
	case RT5350:
		rt2800_init_rfcsr_5350(rt2x00dev);
		break;
	case RT5390:
		rt2800_init_rfcsr_5390(rt2x00dev);
		break;
	case RT5392:
		rt2800_init_rfcsr_5392(rt2x00dev);
		break;
	case RT5592:
		rt2800_init_rfcsr_5592(rt2x00dev);
		break;
	case RT6352:
		rt2800_init_rfcsr_6352(rt2x00dev);
		break;
	}
}