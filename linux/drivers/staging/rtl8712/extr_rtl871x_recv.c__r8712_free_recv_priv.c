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
struct recv_priv {int /*<<< orphan*/  pallocated_frame_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_free_recv_priv (struct recv_priv*) ; 

void _r8712_free_recv_priv(struct recv_priv *precvpriv)
{
	kfree(precvpriv->pallocated_frame_buf);
	r8712_free_recv_priv(precvpriv);
}