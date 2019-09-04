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
struct ssi_protocol {int /*<<< orphan*/  netdev; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int netif_running (int /*<<< orphan*/ ) ; 

int ssip_slave_running(struct hsi_client *master)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(master);
	return netif_running(ssi->netdev);
}