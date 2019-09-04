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
struct cec_pin {int /*<<< orphan*/  adap; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* high ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int cec_pin_read (struct cec_pin*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cec_pin_high(struct cec_pin *pin)
{
	pin->ops->high(pin->adap);
	return cec_pin_read(pin);
}