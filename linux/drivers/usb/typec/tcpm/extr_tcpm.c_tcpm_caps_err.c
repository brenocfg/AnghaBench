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
struct tcpm_port {int dummy; } ;
typedef  enum pdo_err { ____Placeholder_pdo_err } pdo_err ;
typedef  enum pd_pdo_type { ____Placeholder_pd_pdo_type } pd_pdo_type ;

/* Variables and functions */
 int /*<<< orphan*/  APDO_TYPE_PPS ; 
 int PDO_ERR_DUPE_PDO ; 
 int PDO_ERR_DUPE_PPS_APDO ; 
 int PDO_ERR_FIXED_NOT_SORTED ; 
 int PDO_ERR_NO_VSAFE5V ; 
 int PDO_ERR_PDO_TYPE_NOT_IN_ORDER ; 
 int PDO_ERR_PPS_APDO_NOT_SORTED ; 
 int PDO_ERR_VARIABLE_BATT_NOT_SORTED ; 
 int PDO_ERR_VSAFE5V_NOT_FIRST ; 
 int PDO_NO_ERR ; 
#define  PDO_TYPE_APDO 131 
#define  PDO_TYPE_BATT 130 
#define  PDO_TYPE_FIXED 129 
#define  PDO_TYPE_VAR 128 
 scalar_t__ VSAFE5V ; 
 int /*<<< orphan*/  pdo_apdo_type (int /*<<< orphan*/  const) ; 
 scalar_t__ pdo_fixed_voltage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pdo_max_voltage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pdo_min_voltage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pdo_pps_apdo_max_current (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pdo_pps_apdo_max_voltage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pdo_pps_apdo_min_voltage (int /*<<< orphan*/  const) ; 
 scalar_t__ pdo_type (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*) ; 

__attribute__((used)) static enum pdo_err tcpm_caps_err(struct tcpm_port *port, const u32 *pdo,
				  unsigned int nr_pdo)
{
	unsigned int i;

	/* Should at least contain vSafe5v */
	if (nr_pdo < 1)
		return PDO_ERR_NO_VSAFE5V;

	/* The vSafe5V Fixed Supply Object Shall always be the first object */
	if (pdo_type(pdo[0]) != PDO_TYPE_FIXED ||
	    pdo_fixed_voltage(pdo[0]) != VSAFE5V)
		return PDO_ERR_VSAFE5V_NOT_FIRST;

	for (i = 1; i < nr_pdo; i++) {
		if (pdo_type(pdo[i]) < pdo_type(pdo[i - 1])) {
			return PDO_ERR_PDO_TYPE_NOT_IN_ORDER;
		} else if (pdo_type(pdo[i]) == pdo_type(pdo[i - 1])) {
			enum pd_pdo_type type = pdo_type(pdo[i]);

			switch (type) {
			/*
			 * The remaining Fixed Supply Objects, if
			 * present, shall be sent in voltage order;
			 * lowest to highest.
			 */
			case PDO_TYPE_FIXED:
				if (pdo_fixed_voltage(pdo[i]) <=
				    pdo_fixed_voltage(pdo[i - 1]))
					return PDO_ERR_FIXED_NOT_SORTED;
				break;
			/*
			 * The Battery Supply Objects and Variable
			 * supply, if present shall be sent in Minimum
			 * Voltage order; lowest to highest.
			 */
			case PDO_TYPE_VAR:
			case PDO_TYPE_BATT:
				if (pdo_min_voltage(pdo[i]) <
				    pdo_min_voltage(pdo[i - 1]))
					return PDO_ERR_VARIABLE_BATT_NOT_SORTED;
				else if ((pdo_min_voltage(pdo[i]) ==
					  pdo_min_voltage(pdo[i - 1])) &&
					 (pdo_max_voltage(pdo[i]) ==
					  pdo_max_voltage(pdo[i - 1])))
					return PDO_ERR_DUPE_PDO;
				break;
			/*
			 * The Programmable Power Supply APDOs, if present,
			 * shall be sent in Maximum Voltage order;
			 * lowest to highest.
			 */
			case PDO_TYPE_APDO:
				if (pdo_apdo_type(pdo[i]) != APDO_TYPE_PPS)
					break;

				if (pdo_pps_apdo_max_voltage(pdo[i]) <
				    pdo_pps_apdo_max_voltage(pdo[i - 1]))
					return PDO_ERR_PPS_APDO_NOT_SORTED;
				else if (pdo_pps_apdo_min_voltage(pdo[i]) ==
					  pdo_pps_apdo_min_voltage(pdo[i - 1]) &&
					 pdo_pps_apdo_max_voltage(pdo[i]) ==
					  pdo_pps_apdo_max_voltage(pdo[i - 1]) &&
					 pdo_pps_apdo_max_current(pdo[i]) ==
					  pdo_pps_apdo_max_current(pdo[i - 1]))
					return PDO_ERR_DUPE_PPS_APDO;
				break;
			default:
				tcpm_log_force(port, " Unknown pdo type");
			}
		}
	}

	return PDO_NO_ERR;
}