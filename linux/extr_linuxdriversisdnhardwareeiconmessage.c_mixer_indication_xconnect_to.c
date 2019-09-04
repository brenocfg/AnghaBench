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
typedef  scalar_t__ word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void mixer_indication_xconnect_to(dword Id, PLCI *plci, byte *msg, word length)
{

	dbug(1, dprintf("[%06lx] %s,%d: mixer_indication_xconnect_to %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, (int) length));

}