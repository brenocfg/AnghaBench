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
struct TYPE_2__ {int /*<<< orphan*/  (* low ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cec_pin_update (struct cec_pin*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cec_pin_low(struct cec_pin *pin)
{
	pin->ops->low(pin->adap);
	cec_pin_update(pin, false, false);
}