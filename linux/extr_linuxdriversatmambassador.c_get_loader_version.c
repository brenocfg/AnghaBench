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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
struct TYPE_6__ {TYPE_1__ payload; } ;
typedef  TYPE_2__ loader_block ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_LOAD ; 
 int /*<<< orphan*/  PRINTD (int,char*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int do_loader_command (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_version_number ; 

__attribute__((used)) static int get_loader_version(loader_block *lb, const amb_dev *dev,
			      u32 *version)
{
  int res;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "get_loader_version");
  
  res = do_loader_command (lb, dev, get_version_number);
  if (res)
    return res;
  if (version)
    *version = be32_to_cpu (lb->payload.version);
  return 0;
}