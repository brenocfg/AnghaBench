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
struct tse_buffer {int /*<<< orphan*/  lh; } ;
struct altera_tse_private {int /*<<< orphan*/  rxlisthd; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
queue_rx(struct altera_tse_private *priv, struct tse_buffer *buffer)
{
	list_add_tail(&buffer->lh, &priv->rxlisthd);
}