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
struct nand_chip {int dummy; } ;
struct docg4_priv {int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_bch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void docg4_detach_chip(struct nand_chip *chip)
{
	struct docg4_priv *doc = (struct docg4_priv *)(chip + 1);

	free_bch(doc->bch);
}