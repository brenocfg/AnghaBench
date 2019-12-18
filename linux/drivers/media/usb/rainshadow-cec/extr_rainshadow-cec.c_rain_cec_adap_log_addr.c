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
typedef  int u8 ;
struct rain {int dummy; } ;
struct cec_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CEC_LOG_ADDR_INVALID ; 
 int CEC_LOG_ADDR_UNREGISTERED ; 
 struct rain* cec_get_drvdata (struct cec_adapter*) ; 
 int rain_send_and_wait (struct rain*,int*,char*) ; 
 int /*<<< orphan*/  snprintf (int*,int,char*,int) ; 

__attribute__((used)) static int rain_cec_adap_log_addr(struct cec_adapter *adap, u8 log_addr)
{
	struct rain *rain = cec_get_drvdata(adap);
	u8 cmd[16];

	if (log_addr == CEC_LOG_ADDR_INVALID)
		log_addr = CEC_LOG_ADDR_UNREGISTERED;
	snprintf(cmd, sizeof(cmd), "A %x", log_addr);
	return rain_send_and_wait(rain, cmd, "ADR");
}