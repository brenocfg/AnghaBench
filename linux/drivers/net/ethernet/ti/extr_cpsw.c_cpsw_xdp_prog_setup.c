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
struct netdev_bpf {struct bpf_prog* prog; } ;
struct TYPE_3__ {int /*<<< orphan*/  prog; } ;
struct cpsw_priv {TYPE_1__ xdpi; int /*<<< orphan*/  xdp_prog; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 int /*<<< orphan*/  xdp_attachment_flags_ok (TYPE_1__*,struct netdev_bpf*) ; 
 int /*<<< orphan*/  xdp_attachment_setup (TYPE_1__*,struct netdev_bpf*) ; 

__attribute__((used)) static int cpsw_xdp_prog_setup(struct cpsw_priv *priv, struct netdev_bpf *bpf)
{
	struct bpf_prog *prog = bpf->prog;

	if (!priv->xdpi.prog && !prog)
		return 0;

	if (!xdp_attachment_flags_ok(&priv->xdpi, bpf))
		return -EBUSY;

	WRITE_ONCE(priv->xdp_prog, prog);

	xdp_attachment_setup(&priv->xdpi, bpf);

	return 0;
}