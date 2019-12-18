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
struct TYPE_2__ {void* os_type; void* mad_version; void* partition_number; int /*<<< orphan*/  partition_name; int /*<<< orphan*/  srp_version; } ;
struct ibmvscsi_host_data {TYPE_1__ madapter_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRP_MAD_OS_LINUX ; 
 int /*<<< orphan*/  SRP_MAD_VERSION_1 ; 
 int /*<<< orphan*/  SRP_VERSION ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  partition_name ; 
 int /*<<< orphan*/  partition_number ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_adapter_info(struct ibmvscsi_host_data *hostdata)
{
	memset(&hostdata->madapter_info, 0x00,
			sizeof(hostdata->madapter_info));

	dev_info(hostdata->dev, "SRP_VERSION: %s\n", SRP_VERSION);
	strcpy(hostdata->madapter_info.srp_version, SRP_VERSION);

	strncpy(hostdata->madapter_info.partition_name, partition_name,
			sizeof(hostdata->madapter_info.partition_name));

	hostdata->madapter_info.partition_number =
					cpu_to_be32(partition_number);

	hostdata->madapter_info.mad_version = cpu_to_be32(SRP_MAD_VERSION_1);
	hostdata->madapter_info.os_type = cpu_to_be32(SRP_MAD_OS_LINUX);
}