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
typedef  int /*<<< orphan*/  u16 ;
struct pulse8 {int /*<<< orphan*/  adap; } ;
struct cec_log_addrs {int dummy; } ;

/* Variables and functions */
 int cec_s_log_addrs (int /*<<< orphan*/ ,struct cec_log_addrs*,int) ; 
 int /*<<< orphan*/  cec_s_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pulse8_apply_persistent_config(struct pulse8 *pulse8,
					  struct cec_log_addrs *log_addrs,
					  u16 pa)
{
	int err;

	err = cec_s_log_addrs(pulse8->adap, log_addrs, false);
	if (err)
		return err;

	cec_s_phys_addr(pulse8->adap, pa, false);

	return 0;
}