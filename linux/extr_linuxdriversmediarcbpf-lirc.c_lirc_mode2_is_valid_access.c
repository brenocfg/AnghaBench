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
struct bpf_prog {int dummy; } ;
struct bpf_insn_access_aux {int dummy; } ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;

/* Variables and functions */
 int BPF_READ ; 

__attribute__((used)) static bool lirc_mode2_is_valid_access(int off, int size,
				       enum bpf_access_type type,
				       const struct bpf_prog *prog,
				       struct bpf_insn_access_aux *info)
{
	/* We have one field of u32 */
	return type == BPF_READ && off == 0 && size == sizeof(u32);
}