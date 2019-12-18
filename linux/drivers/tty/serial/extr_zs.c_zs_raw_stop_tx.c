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
struct zs_port {int tx_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  RES_Tx_P ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_raw_stop_tx(struct zs_port *zport)
{
	write_zsreg(zport, R0, RES_Tx_P);
	zport->tx_stopped = 1;
}