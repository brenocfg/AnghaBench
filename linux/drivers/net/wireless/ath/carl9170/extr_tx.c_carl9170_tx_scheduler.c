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
struct ar9170 {scalar_t__ tx_schedule; scalar_t__ tx_ampdu_schedule; } ;

/* Variables and functions */
 int /*<<< orphan*/  carl9170_tx (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_tx_ampdu (struct ar9170*) ; 

void carl9170_tx_scheduler(struct ar9170 *ar)
{

	if (ar->tx_ampdu_schedule)
		carl9170_tx_ampdu(ar);

	if (ar->tx_schedule)
		carl9170_tx(ar);
}