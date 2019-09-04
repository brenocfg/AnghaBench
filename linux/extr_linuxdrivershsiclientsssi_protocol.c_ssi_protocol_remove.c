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
struct ssi_protocol {int /*<<< orphan*/  netdev; int /*<<< orphan*/  link; } ;
struct hsi_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_client_set_drvdata (struct hsi_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ssi_protocol*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_free_cmds (struct ssi_protocol*) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssi_protocol_remove(struct device *dev)
{
	struct hsi_client *cl = to_hsi_client(dev);
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);

	list_del(&ssi->link);
	unregister_netdev(ssi->netdev);
	ssip_free_cmds(ssi);
	hsi_client_set_drvdata(cl, NULL);
	kfree(ssi);

	return 0;
}