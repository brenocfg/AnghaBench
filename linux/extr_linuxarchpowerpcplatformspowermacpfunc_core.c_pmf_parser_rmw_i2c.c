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
typedef  int /*<<< orphan*/  u32 ;
struct pmf_handlers {int dummy; } ;
struct pmf_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_BLOB (char*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_PARSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMF_PARSE_CALL (int /*<<< orphan*/ ,struct pmf_cmd*,struct pmf_handlers*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,void const*) ; 
 int /*<<< orphan*/  pmf_next32 (struct pmf_cmd*) ; 
 void* pmf_next_blob (struct pmf_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmw_i2c ; 

__attribute__((used)) static int pmf_parser_rmw_i2c(struct pmf_cmd *cmd, struct pmf_handlers *h)
{
	u32 maskbytes = pmf_next32(cmd);
	u32 valuesbytes = pmf_next32(cmd);
	u32 totalbytes = pmf_next32(cmd);
	const void *maskblob = pmf_next_blob(cmd, maskbytes);
	const void *valuesblob = pmf_next_blob(cmd, valuesbytes);

	LOG_PARSE("pmf: rmw_i2c(maskbytes: %ud, valuebytes: %ud, "
		  "totalbytes: %d) ...\n",
		  maskbytes, valuesbytes, totalbytes);
	LOG_BLOB("pmf:   mask data: \n", maskblob, maskbytes);
	LOG_BLOB("pmf:   values data: \n", valuesblob, valuesbytes);

	PMF_PARSE_CALL(rmw_i2c, cmd, h, maskbytes, valuesbytes, totalbytes,
		       maskblob, valuesblob);
}