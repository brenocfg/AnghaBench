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
struct rocker {struct ofdpa* wpriv; } ;
struct ofdpa_port {int dummy; } ;
struct ofdpa {scalar_t__ fib_aborted; } ;
struct fib_nh {int /*<<< orphan*/  fib_nh_flags; int /*<<< orphan*/  fib_nh_dev; } ;
struct fib_entry_notifier_info {int /*<<< orphan*/  tb_id; int /*<<< orphan*/  fi; int /*<<< orphan*/  dst_len; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTNH_F_OFFLOAD ; 
 struct fib_nh* fib_info_nh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct ofdpa_port* ofdpa_port_dev_lower_find (int /*<<< orphan*/ ,struct rocker*) ; 
 int ofdpa_port_fib_ipv4 (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_fib4_add(struct rocker *rocker,
			  const struct fib_entry_notifier_info *fen_info)
{
	struct ofdpa *ofdpa = rocker->wpriv;
	struct ofdpa_port *ofdpa_port;
	struct fib_nh *nh;
	int err;

	if (ofdpa->fib_aborted)
		return 0;
	nh = fib_info_nh(fen_info->fi, 0);
	ofdpa_port = ofdpa_port_dev_lower_find(nh->fib_nh_dev, rocker);
	if (!ofdpa_port)
		return 0;
	err = ofdpa_port_fib_ipv4(ofdpa_port, htonl(fen_info->dst),
				  fen_info->dst_len, fen_info->fi,
				  fen_info->tb_id, 0);
	if (err)
		return err;
	nh->fib_nh_flags |= RTNH_F_OFFLOAD;
	return 0;
}