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
struct nfp_flower_ext_meta {int /*<<< orphan*/  nfp_flow_key_layer2; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_flower_compile_ext_meta(struct nfp_flower_ext_meta *frame, u32 key_ext)
{
	frame->nfp_flow_key_layer2 = cpu_to_be32(key_ext);
}