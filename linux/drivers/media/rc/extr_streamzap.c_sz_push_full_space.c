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
struct streamzap_ir {int sum; } ;
struct ir_raw_event {int pulse; int duration; } ;

/* Variables and functions */
 int SZ_RESOLUTION ; 
 int US_TO_NS (int) ; 
 int /*<<< orphan*/  sz_push (struct streamzap_ir*,struct ir_raw_event) ; 

__attribute__((used)) static void sz_push_full_space(struct streamzap_ir *sz,
			       unsigned char value)
{
	struct ir_raw_event rawir = {};

	rawir.pulse = false;
	rawir.duration = ((int) value) * SZ_RESOLUTION;
	rawir.duration += SZ_RESOLUTION / 2;
	sz->sum += rawir.duration;
	rawir.duration = US_TO_NS(rawir.duration);
	sz_push(sz, rawir);
}