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
struct via_pll_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cle266_encode_pll (struct via_pll_config) ; 
 int /*<<< orphan*/  cle266_set_primary_pll_encoded (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cle266_set_primary_pll(struct via_pll_config config)
{
	cle266_set_primary_pll_encoded(cle266_encode_pll(config));
}