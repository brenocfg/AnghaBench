#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssi_protocol {TYPE_1__* cl; } ;
struct hsi_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_error (TYPE_1__*) ; 

void ssip_reset_event(struct hsi_client *master)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(master);
	dev_err(&ssi->cl->device, "CMT reset detected!\n");
	ssip_error(ssi->cl);
}