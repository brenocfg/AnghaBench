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
struct vas_window {int cop; int tx_win; struct vas_window* paste_kaddr; int /*<<< orphan*/  user_win; int /*<<< orphan*/  wcreds_max; int /*<<< orphan*/  pid; int /*<<< orphan*/  nx_win; struct vas_window* rxwin; } ;
struct vas_winctx {int dummy; } ;
struct vas_tx_win_attr {scalar_t__ wcreds_max; int /*<<< orphan*/  user_win; int /*<<< orphan*/  pid; int /*<<< orphan*/  pswid; } ;
struct vas_instance {int dummy; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int EINVAL ; 
 struct vas_window* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct vas_window*) ; 
 int PTR_ERR (struct vas_window*) ; 
 int /*<<< orphan*/  VAS_WCREDS_DEFAULT ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  decode_pswid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 struct vas_instance* find_vas_instance (int) ; 
 struct vas_window* get_vinst_rxwin (struct vas_instance*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_winctx_for_txwin (struct vas_window*,struct vas_tx_win_attr*,struct vas_winctx*) ; 
 int /*<<< orphan*/  init_winctx_regs (struct vas_window*,struct vas_winctx*) ; 
 struct vas_window* map_paste_region (struct vas_window*) ; 
 int /*<<< orphan*/  pr_devel (char*,int,...) ; 
 int /*<<< orphan*/  put_rx_win (struct vas_window*) ; 
 int set_thread_uses_vas () ; 
 int /*<<< orphan*/  set_vinst_win (struct vas_instance*,struct vas_window*) ; 
 int /*<<< orphan*/  trace_vas_tx_win_open (int /*<<< orphan*/ ,int,int,struct vas_tx_win_attr*) ; 
 int /*<<< orphan*/  tx_win_args_valid (int,struct vas_tx_win_attr*) ; 
 struct vas_window* vas_window_alloc (struct vas_instance*) ; 
 int /*<<< orphan*/  vas_window_free (struct vas_window*) ; 

struct vas_window *vas_tx_win_open(int vasid, enum vas_cop_type cop,
			struct vas_tx_win_attr *attr)
{
	int rc;
	struct vas_window *txwin;
	struct vas_window *rxwin;
	struct vas_winctx winctx;
	struct vas_instance *vinst;

	trace_vas_tx_win_open(current, vasid, cop, attr);

	if (!tx_win_args_valid(cop, attr))
		return ERR_PTR(-EINVAL);

	/*
	 * If caller did not specify a vasid but specified the PSWID of a
	 * receive window (applicable only to FTW windows), use the vasid
	 * from that receive window.
	 */
	if (vasid == -1 && attr->pswid)
		decode_pswid(attr->pswid, &vasid, NULL);

	vinst = find_vas_instance(vasid);
	if (!vinst) {
		pr_devel("vasid %d not found!\n", vasid);
		return ERR_PTR(-EINVAL);
	}

	rxwin = get_vinst_rxwin(vinst, cop, attr->pswid);
	if (IS_ERR(rxwin)) {
		pr_devel("No RxWin for vasid %d, cop %d\n", vasid, cop);
		return rxwin;
	}

	txwin = vas_window_alloc(vinst);
	if (IS_ERR(txwin)) {
		rc = PTR_ERR(txwin);
		goto put_rxwin;
	}

	txwin->cop = cop;
	txwin->tx_win = 1;
	txwin->rxwin = rxwin;
	txwin->nx_win = txwin->rxwin->nx_win;
	txwin->pid = attr->pid;
	txwin->user_win = attr->user_win;
	txwin->wcreds_max = attr->wcreds_max ?: VAS_WCREDS_DEFAULT;

	init_winctx_for_txwin(txwin, attr, &winctx);

	init_winctx_regs(txwin, &winctx);

	/*
	 * If its a kernel send window, map the window address into the
	 * kernel's address space. For user windows, user must issue an
	 * mmap() to map the window into their address space.
	 *
	 * NOTE: If kernel ever resubmits a user CRB after handling a page
	 *	 fault, we will need to map this into kernel as well.
	 */
	if (!txwin->user_win) {
		txwin->paste_kaddr = map_paste_region(txwin);
		if (IS_ERR(txwin->paste_kaddr)) {
			rc = PTR_ERR(txwin->paste_kaddr);
			goto free_window;
		}
	} else {
		/*
		 * A user mapping must ensure that context switch issues
		 * CP_ABORT for this thread.
		 */
		rc = set_thread_uses_vas();
		if (rc)
			goto free_window;
	}

	set_vinst_win(vinst, txwin);

	return txwin;

free_window:
	vas_window_free(txwin);

put_rxwin:
	put_rx_win(rxwin);
	return ERR_PTR(rc);

}