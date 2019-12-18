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
struct tun_struct {int /*<<< orphan*/  filter_prog; } ;
struct tun_prog {int /*<<< orphan*/  prog; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int bpf_prog_run_clear_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct tun_prog* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int run_ebpf_filter(struct tun_struct *tun,
				    struct sk_buff *skb,
				    int len)
{
	struct tun_prog *prog = rcu_dereference(tun->filter_prog);

	if (prog)
		len = bpf_prog_run_clear_cb(prog->prog, skb);

	return len;
}