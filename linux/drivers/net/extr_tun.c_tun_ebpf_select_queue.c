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
typedef  int u32 ;
typedef  int u16 ;
struct tun_struct {int /*<<< orphan*/  steering_prog; int /*<<< orphan*/  numqueues; } ;
struct tun_prog {int /*<<< orphan*/  prog; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int bpf_prog_run_clear_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct tun_prog* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 tun_ebpf_select_queue(struct tun_struct *tun, struct sk_buff *skb)
{
	struct tun_prog *prog;
	u32 numqueues;
	u16 ret = 0;

	numqueues = READ_ONCE(tun->numqueues);
	if (!numqueues)
		return 0;

	prog = rcu_dereference(tun->steering_prog);
	if (prog)
		ret = bpf_prog_run_clear_cb(prog->prog, skb);

	return ret % numqueues;
}