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
struct mvneta_tx_queue {int dummy; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_txq_sent_desc_dec (struct mvneta_port*,struct mvneta_tx_queue*,int) ; 
 int mvneta_txq_sent_desc_num_get (struct mvneta_port*,struct mvneta_tx_queue*) ; 

__attribute__((used)) static int mvneta_txq_sent_desc_proc(struct mvneta_port *pp,
				     struct mvneta_tx_queue *txq)
{
	int sent_desc;

	/* Get number of sent descriptors */
	sent_desc = mvneta_txq_sent_desc_num_get(pp, txq);

	/* Decrement sent descriptors counter */
	if (sent_desc)
		mvneta_txq_sent_desc_dec(pp, txq, sent_desc);

	return sent_desc;
}