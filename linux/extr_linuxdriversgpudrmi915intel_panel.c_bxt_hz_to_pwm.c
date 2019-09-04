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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KHz (int) ; 

__attribute__((used)) static u32 bxt_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	return DIV_ROUND_CLOSEST(KHz(19200), pwm_freq_hz);
}