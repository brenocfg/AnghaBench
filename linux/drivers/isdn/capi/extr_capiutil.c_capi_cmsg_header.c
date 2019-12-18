#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct TYPE_5__ {int /*<<< orphan*/  adrController; } ;
struct TYPE_6__ {TYPE_1__ adr; void* Messagenumber; void* Subcommand; void* Command; void* ApplId; } ;
typedef  TYPE_2__ _cmsg ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

unsigned capi_cmsg_header(_cmsg *cmsg, u16 _ApplId,
			  u8 _Command, u8 _Subcommand,
			  u16 _Messagenumber, u32 _Controller)
{
	memset(cmsg, 0, sizeof(_cmsg));
	cmsg->ApplId = _ApplId;
	cmsg->Command = _Command;
	cmsg->Subcommand = _Subcommand;
	cmsg->Messagenumber = _Messagenumber;
	cmsg->adr.adrController = _Controller;
	return 0;
}