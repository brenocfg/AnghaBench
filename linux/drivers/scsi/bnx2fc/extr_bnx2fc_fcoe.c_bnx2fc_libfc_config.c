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
struct libfc_function_template {int dummy; } ;
struct fc_lport {int /*<<< orphan*/  tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_libfc_fcn_templ ; 
 int /*<<< orphan*/  fc_disc_config (struct fc_lport*,struct fc_lport*) ; 
 int /*<<< orphan*/  fc_disc_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_elsct_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_exch_init (struct fc_lport*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bnx2fc_libfc_config(struct fc_lport *lport)
{

	/* Set the function pointers set by bnx2fc driver */
	memcpy(&lport->tt, &bnx2fc_libfc_fcn_templ,
		sizeof(struct libfc_function_template));
	fc_elsct_init(lport);
	fc_exch_init(lport);
	fc_disc_init(lport);
	fc_disc_config(lport, lport);
	return 0;
}