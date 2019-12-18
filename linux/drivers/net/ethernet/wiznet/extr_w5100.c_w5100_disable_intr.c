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
struct w5100_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  w5100_socket_intr_mask (struct w5100_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w5100_disable_intr(struct w5100_priv *priv)
{
	w5100_socket_intr_mask(priv, 0);
}