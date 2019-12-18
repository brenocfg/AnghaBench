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
typedef  void* u8 ;
struct TYPE_2__ {int posted; int siga_mode; int sigb_mode; void* sigb; void* siga; } ;
struct nfp_cpp_explicit {TYPE_1__ cmd; } ;
typedef  enum nfp_cpp_explicit_signal_mode { ____Placeholder_nfp_cpp_explicit_signal_mode } nfp_cpp_explicit_signal_mode ;

/* Variables and functions */

int nfp_cpp_explicit_set_posted(struct nfp_cpp_explicit *expl, int posted,
				u8 siga,
				enum nfp_cpp_explicit_signal_mode siga_mode,
				u8 sigb,
				enum nfp_cpp_explicit_signal_mode sigb_mode)
{
	expl->cmd.posted = posted;
	expl->cmd.siga = siga;
	expl->cmd.sigb = sigb;
	expl->cmd.siga_mode = siga_mode;
	expl->cmd.sigb_mode = sigb_mode;

	return 0;
}