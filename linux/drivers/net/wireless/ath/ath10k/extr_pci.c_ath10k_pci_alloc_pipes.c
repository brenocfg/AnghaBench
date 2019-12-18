#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath10k_pci_pipe {int pipe_num; size_t buf_sz; int /*<<< orphan*/ * ce_hdl; struct ath10k* hif_ce_state; } ;
struct ath10k_pci {int /*<<< orphan*/ * ce_diag; struct ath10k_pci_pipe* pipe_info; } ;
struct ath10k_ce {int /*<<< orphan*/ * ce_states; } ;
struct ath10k {int dummy; } ;
struct TYPE_3__ {scalar_t__ src_sz_max; } ;

/* Variables and functions */
 int CE_COUNT ; 
 int CE_DIAG_PIPE ; 
 int ath10k_ce_alloc_pipe (struct ath10k*,int,TYPE_1__*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,int) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 TYPE_1__* host_ce_config_wlan ; 

int ath10k_pci_alloc_pipes(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	struct ath10k_pci_pipe *pipe;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	int i, ret;

	for (i = 0; i < CE_COUNT; i++) {
		pipe = &ar_pci->pipe_info[i];
		pipe->ce_hdl = &ce->ce_states[i];
		pipe->pipe_num = i;
		pipe->hif_ce_state = ar;

		ret = ath10k_ce_alloc_pipe(ar, i, &host_ce_config_wlan[i]);
		if (ret) {
			ath10k_err(ar, "failed to allocate copy engine pipe %d: %d\n",
				   i, ret);
			return ret;
		}

		/* Last CE is Diagnostic Window */
		if (i == CE_DIAG_PIPE) {
			ar_pci->ce_diag = pipe->ce_hdl;
			continue;
		}

		pipe->buf_sz = (size_t)(host_ce_config_wlan[i].src_sz_max);
	}

	return 0;
}