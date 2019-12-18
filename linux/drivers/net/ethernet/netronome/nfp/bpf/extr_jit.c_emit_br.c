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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_prog {int dummy; } ;
typedef  enum br_mask { ____Placeholder_br_mask } br_mask ;

/* Variables and functions */
 int /*<<< orphan*/  RELO_BR_REL ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_br(struct nfp_prog *nfp_prog, enum br_mask mask, u16 addr, u8 defer)
{
	emit_br_relo(nfp_prog, mask, addr, defer, RELO_BR_REL);
}